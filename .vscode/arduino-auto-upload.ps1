param(
    [string]$WorkspaceFolder
)

$json = arduino-cli board list --json | ConvertFrom-Json

$fqbn = $null
$port = $null

foreach ($entry in $json.detected_ports) {
    foreach ($board in $entry.matching_boards) {
        if ($board.name -match "Arduino") {
            $fqbn = $board.fqbn
            $port = $entry.port.address
            break
        }
    }

    if ($port -and $fqbn) {
        break
    }
}

if (-not $port -or -not $fqbn) {
    throw "No matching Arduino board found"
}

Write-Host ("Using board: " + $fqbn)
Write-Host ("Using port: " + $port)

arduino-cli compile --fqbn $fqbn $WorkspaceFolder
if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}

arduino-cli upload -p $port --fqbn $fqbn $WorkspaceFolder
exit $LASTEXITCODE