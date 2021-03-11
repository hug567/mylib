function prompt {
       $dateTime = get-date -Format "HH:mm:ss"
       $currentDirectory = $(Get-Location)

       write-host "" -ForegroundColor White
       write-host "[PS] " -NoNewline -ForegroundColor Green
       write-host "$(Convert-Path $currentDirectory) " -NoNewline -ForegroundColor Yellow
       write-host "<$dateTime>" -ForegroundColor Green
       write-host " > " -NoNewline -ForegroundColor Red

       return " "
}