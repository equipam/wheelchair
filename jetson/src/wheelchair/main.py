#TODO #8 Create jetson nano main routine logic

import typer
from wheelchair.sslidar_driver import SSLidarDriver

app = typer.Typer()

@app.command()
def main():
    raise typer.Exit(1)

if __name__ == "__main__":
    app()
