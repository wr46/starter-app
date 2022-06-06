# Starter App

## Description

C++ application to execute local scripts and/or application. \
The purpose of this application is to allow to run multiple automations scripts using one single documented application anywhere by CLI and add new scripts without changing the starter application.

## How it works

- **starter** application is installed in */usr/local/bin*
- configuration folder is created in */home/user/.starter*.
- *config.yaml* file in *~/.starter/* folder set what commands will be allowed **example:** [config.yaml](./src/config.yaml.template)
- scripts and applications to execute must be added to *~/.starter/executables*

## Example

Execute the object with flag *flag-example* configured in *config.yaml* file:

```bash
    starter -e flag-example
```

Print config.yaml file content:

```bash
    starter -s
```

Print **starter** application help:

```bash
    starter -h
```

## config.yaml file

*config.yaml* file define what executables can be xecuted

```yaml
    - flag: a-script # <- The flag used in "starter -e flag"
    description: Execute script A
    exec: "a_script.sh" # <- The script name in ~/.starter/executables/ to be executed
    ...
```

## Makefile

Makefile help to build, install and develop the application

```bash
    # Build satrter application
    make starter

    # Copy application binary to /uss/local/bin and setup ~/.starter folder
    make install

    # Run application with example-flag (used for development)
    make run-exec flag=example-flag

    # Remove application binary
    make clean
```
