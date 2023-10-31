$command = "g++"
$output = "-o main"
$inputFile = ".\Source.cpp"
$links = "-lfreeglut -lglew32 -lopengl32"

echo "$command $output $inputFile $links"

# Set-Location -Path "C:\\Users\\DELL\\source\\repos\\lab01"


# Run the command
Invoke-Expression "$command $output $inputFile $links"