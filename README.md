## Introduction
**MurCes** is a Minecraft server configuration tool. While setting up a Minecraft server is nothing
too difficult &mdash; this tool makes it simpler for users inexperienced with a terminal by providing
a user-friendly terminal interface.

For more information, check out the `doc` directory.
> **Note**:
This is still in early development and only supports Linux devices. It *can* be run on Windows via
[Mingw-w64](https://en.wikipedia.org/wiki/Mingw-w64), [Cygwin](https://en.wikipedia.org/wiki/Cygwin),
or [Windows Subsystem for Linux](https://en.wikipedia.org/wiki/Windows_Subsystem_for_Linux) (WSL).
WSL is only supported from Windows 10 onwards. If you are using Windows versions prior to Windows 10
Mingw-w64 and Cygwin are better alternatives.

## Obtaining sources
MurCes uses the [precursor](https://codeberg.org/nilabhro/precursor) library as a submodule. Therefore,
to get the source code on your machine, you'll have to run the following command:
```sh
git clone --recurse-submodules https://github.com/DeployedReject/murces.git MurCes
```
If you did not clone the repository with the `--recurse-submodules` flag, you can later update the
submodule(s) with the following command:
```sh
git submodule update --init --recursive --remote --merge
```

## Building
This repository is divided into two modules: the frontend (i.e. the terminal user interface) and
the backend (i.e. the orchestrator). You will have to build each module separately. 

To build the terminal user interface (a.k.a. TUI) you will have to run the following command:
```sh
make -C c
```

Finally, to build the orchestrator, you will need to run this command
```sh
mvn clean package
mv java/orchestrator/target/murces-orchestrator.jar .
```

### Want to rebuild?
Just rerun the same commands but force move the `murces-orchestrator` binary since you presumably
do not need to old one anymore. However, if you want to keep the old one, here's how you can do it:
```sh
make -C c
mvn clean package
mv murces-orchestrator murces-orchestrator.jar.old && mv java/orchestrator/target/murces-orchestrator.jar .
```

> **Note**:
To build a native binary for `murces-orchestrator`, you will need to run `mvn clean package -Pnative`
instead of `mvn clean package`. This requires you to have
[GraalVM](https://en.wikipedia.org/wiki/GraalVM).

## `compile_commands.json`
If using a LSP (Language Server Protocol) you can use the `compile_commands.json` file. In your LSP's configuration file, you can explictly point it towards the `compile_commands.json` file. To generate the
JSON file, run the following commands:
```sh
pip install compiledb
compiledb make
```

If this command fails, you probably need a virtual environment to run `pip` commands:
```sh
python -m venv venv
source venv/bin/activate
pip install compiledb
compiledb make -C c
```
To exit this virtual environment, simply run the following command:
```sh
deactivate
```

Here is an example of how you might want to configure
[clangd](https://clangd.llvm.org/):
1. Create a `.clangd` file in the project's root directory.
2. Copy and paste the following:
```yaml
CompileFlags:
    CompilationDatabase: c
```
It should use a relative path from your .clangd file if you decide to create it somewhere else.

## Issues
Any bugs, suggestions, or feedback must be submitted to the project's issue tracker &mdash; either on
[GitHub](https://github.com/DeployedReject/murces/issues) or
[Codeberg](https://codeberg.org/nilabhro/MurCes/issues).