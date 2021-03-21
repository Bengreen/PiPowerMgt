#!/usr/bin/venv python
import click
from .watchdog import PiWatchDog


@click.group()
def cli():
    pass


@cli.command()
@click.argument("id", type=int)
@click.argument("state", type=click.Choice(["on", "off"]))
@click.option("--address", "address", type=int, default=0x08)
def fan(address, id, state):
    click.echo(f"Turn {state} Fan {id}")
    watchdog = PiWatchDog(address)
    if state == "on":
        click.echo("ON")
        watchdog.fanOn(id)
    else:
        click.echo("OFF")
        watchdog.fanOff(id)


if __name__ == "__main__":
    cli()