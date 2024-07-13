def convert_to_xyz(input_file, output_file, element_symbol="C"):
    with open(input_file, 'r') as infile:
        lines = infile.readlines()

    num_atoms = len(lines)

    with open(output_file, 'w') as outfile:
        outfile.write(f"{num_atoms}\n")
        outfile.write("Atoms\n")
        for line in lines:
            x, y, z = line.strip().split(',')
            outfile.write(f"{element_symbol} {x} {y} {z}\n")

# Usage
convert_to_xyz("coordinates_3.txt", "surface.xyz")
