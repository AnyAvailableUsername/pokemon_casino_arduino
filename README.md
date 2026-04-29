# setup arduino cli

- download arduino-cli and vscode
- add cli to path (restart vscode)
- init arduino-cli

```bash
arduino-cli config init
arduino-cli core update-index
arduino-cli core install arduino:avr
```

- to compile sketch

```bash
arduino-cli compile --fqbn arduino:avr:micro .
```

- upload

```bash
arduino-cli upload -p COM18 --fqbn arduino:avr:micro .
```

- serial monitor

```bash
arduino-cli monitor -p COM18 -c baudrate=9600
```

