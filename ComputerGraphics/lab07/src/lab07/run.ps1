# Define the command you want to run
$command = "g++"
$output = "-o main"
$headers = "Canvas.h"
$inputFile = ".\Star.cpp"
$links = "-lfreeglut -lglew32 -lglu32 -lopengl32"

echo "$command $output $inputFile $links"

# Set-Location -Path "C:\\Users\\Lenovo Admin\\Desktop\\CG\\lab 11"


# Run the command
Invoke-Expression "$command $output $inputFile  $links"
Invoke-Expression "./main.exe"