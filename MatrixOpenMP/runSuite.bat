SET matrixPath=D:\Programming\VS2015\MatrixGenerator\MatrixGenerator
for /l %%i in (1,1,5) do for /l %%j in (1,1,3) do call Debug\MatrixOpenMP.exe %matrixPath%\first%%i.txt %matrixPath%\second%%i.txt output%%i.txt >> results.txt 2>&1