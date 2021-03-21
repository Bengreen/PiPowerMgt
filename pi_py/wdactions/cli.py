#!/usr/bin/venv python
import click
from .watchdog import PiWatchDog
from .wdsystemd import watchdogd


@click.group()
def cli():
    pass


@cli.command()
@click.argument("id", type=int)
@click.argument("state", type=click.Choice(["on", "off"]))
@click.option("--address", "address", type=int, default=0x08)
def power(address, id, state):
    watchdog = PiWatchDog(address)
    if state == "on":
        click.echo("ON")
        watchdog.powerOn(id)
    else:
        click.echo("OFF")
        watchdog.powerOff(id)
    click.echo(f"Turn {state} Fan {id}")


@cli.command()
@click.argument("id", type=int)
@click.argument("state", type=click.Choice(["on", "off"]))
@click.option("--address", "address", type=int, default=0x08)
def fan(address, id, state):
    watchdog = PiWatchDog(address)
    if state == "on":
        click.echo("ON")
        watchdog.fanOn(id)
    else:
        click.echo("OFF")
        watchdog.fanOff(id)
    click.echo(f"Turn {state} Fan {id}")


@cli.command()
@click.argument("id", type=int)
@click.option("--address", "address", type=int, default=0x08)
@click.option("--on", "on", type=int, default=61)
@click.option("--off", "off", type=int, default=53)
@click.option("--sleep", "sleepinterval", type=int, default=5)
def watch(address, id, on, off, sleepinterval):
    click.echo(f"Starting watchdog for id={id}")
    watchdogd(address, id, on, off, sleepinterval)


if __name__ == "__main__":
    cli()