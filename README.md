# ext-duckdb

An exercise in using LLMs to generate a PHP extension - and to try to fill a gap in available PHP extensions.

I have the duckdb source code in `duckdb/` and the PHP source code in `php-src/` for easy reference.

Based on https://github.com/bogkonstantin/php-extension-hello-world. Original README below.

---

# Base PHP extension in C language with VSCode Debugger setup

Clone this repository and navigate to the directory.  
Want to learn more about PHP extension development? Read more [here](https://bogomolov.tech/php-extension-development/).

### Build image

```bash
docker build --pull --rm -f "Dockerfile" -t php-dev:latest "."
```

### Run container

```bash
docker run --rm --name php-dev -it php-dev bash
```

### Test function

Check if it works from inside the container:
```bash
php -r "echo hello_world() . PHP_EOL;"
```

### Debug configuration for Visual Studio Code

VSCode launch config (tested on Mac M2). Use [Docker Dev containers](https://code.visualstudio.com/docs/devcontainers/containers) in VSCode

```json
{
    "name": "Launch Test Function (gdb)",
    "type": "cppdbg",
    "request": "launch",
    "program": "/usr/local/bin/php",
    "args": [
        "-r",
        "echo hello_world() . PHP_EOL;",
    ],
    "cwd": ".",
    "MIMode": "gdb",
    "additionalSOLibSearchPath": "/php-src;/php-ext",
    "setupCommands": [
        {
            "description": "Enable pretty-printing for gdb",
            "text": "-enable-pretty-printing",
            "ignoreFailures": true
        }
    ]
}
```