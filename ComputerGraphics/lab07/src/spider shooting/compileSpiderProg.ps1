# Define the command you want to run
$command = "g++"
$output = "-o main"
$inputFile = ".\source.cpp"
$headers = "Headers\\spider.h Headers\\point.h Headers\\pixMap.h"
$implementations = ""
$links = "-lfreeglut -lglew32 -lopengl32 -lglu32 -lwinmm"

echo "$command $output $inputFile $headers $implementations $links"

# Set-Location -Path "C:\\Users\\Lenovo Admin\\Desktop\\CG\\spider shooting"

# Run the command
Invoke-Expression "$command $output $inputFile $headers $implementations $links"
