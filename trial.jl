import Pkg ; Pkg.activate("Packmol", shared=true)

using Packmol

input_file = raw "C:/Users/Smart_Coatings/Desktop/Internship/Modeling/water.inp"

run_packmol(input_file)