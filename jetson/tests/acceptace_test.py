from unittest import mock
from typer.testing import CliRunner
from wheelchair.main import app


@mock.patch("wheelchair.main.SSLidar")
@mock.patch("wheelchair.main.Arduino")
def test_collision(mock_arduino, mock_lidar):
    runner = CliRunner()

    mock_lidar.return_value.configure_mock(collision=True)
    mock_arduino.return_value.configure_mock(state=False)

    result = runner.invoke(app, ["--once", "--verbose"])

    mock_arduino.return_value.set_stop_signal.assert_called_with(True)
    assert result.exit_code == 0
    assert "Collision!" in result.output


@mock.patch("wheelchair.main.SSLidar")
@mock.patch("wheelchair.main.Arduino")
def test_no_collision(mock_arduino, mock_lidar):
    runner = CliRunner()

    mock_lidar.return_value.configure_mock(collision=False)
    mock_arduino.return_value.configure_mock(state=True)

    result = runner.invoke(app, ["--once", "--verbose"])

    mock_arduino.return_value.set_stop_signal.assert_called_with(False)
    assert result.exit_code == 0
    assert "Not colliding anymore!" in result.output
