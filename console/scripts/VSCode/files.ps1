[CmdletBinding()]
param([string]$Compiler = 'g++')

$ErrorActionPreference = 'Stop'

try {
    $projectRoot = Split-Path -Parent (Split-Path -Parent $PSScriptRoot)
    $scriptsRoot = Join-Path $projectRoot 'scripts'

    if (-not (Test-Path -LiteralPath $scriptsRoot -PathType Container)) {
        throw "The scripts folder was not found: $scriptsRoot"
    }

    $sourceFiles = @(
        Get-ChildItem -LiteralPath $scriptsRoot -Recurse -File -Filter '*.cpp' |
            Select-Object -ExpandProperty FullName
    )

    $sourceFiles = @($sourceFiles | Sort-Object -Unique)
    if ($sourceFiles.Count -eq 0) {
        throw 'No .cpp files were found in scripts or as main.cpp in the project root.'
    }

    $includeDirectories = @($projectRoot, $scriptsRoot)
    $includeDirectories += @(
        Get-ChildItem -LiteralPath $scriptsRoot -Recurse -Directory |
            Select-Object -ExpandProperty FullName
    )

    $compilerArgs = @()
    foreach ($directory in ($includeDirectories | Sort-Object -Unique)) {
        $compilerArgs += @('-I', $directory)
    }
    $compilerArgs += $sourceFiles

    $argumentsFile = Join-Path $PSScriptRoot 'files.rsp'

    [string[]]$lines = $compilerArgs | ForEach-Object {
        '"' + $_.Replace('\', '/') + '"'
    }

    [System.IO.File]::WriteAllLines(
        $argumentsFile,
        $lines,
        [System.Text.UTF8Encoding]::new($false)
    )

    exit 0
}
catch {
    Write-Error -Message $_.Exception.Message -ErrorAction Continue
    exit 1
}
