#TODO #5 Create jetson nano application acceptance test

from unittest import mock
from typer.testing import CliRunner
from wheelchair.main import app

@mock.patch("src.main.SSLidarDriver")
def test_acceptance(mock_driver):
    runner = CliRunner()
    result = runner.invoke(app, ["--once"])
    assert result.exit_code == 0