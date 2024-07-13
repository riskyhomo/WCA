def xyz_to_lammps_data(input_xyz_file, output_data_file):
    with open(input_xyz_file, 'r') as infile:
        lines = infile.readlines()

    num_atoms = int(lines[0].strip())
    atom_data = lines[2:num_atoms + 2]

    with open(output_data_file, 'w') as outfile:
        # Header
        outfile.write("LAMMPS data file generated from XYZ\n\n")
        # Number of atoms and atom types
        outfile.write(f"{num_atoms} atoms\n")
        outfile.write("2 atom types\n\n")  # Assuming 2 types: O and H for water

        # Box dimensions (adjust as necessary)
        outfile.write("0.0 300.0 xlo xhi\n")
        outfile.write("0.0 300.0 ylo yhi\n")
        outfile.write("0.0 300.0 zlo zhi\n\n")

        # Atoms section
        outfile.write("Atoms\n\n")
        for i, line in enumerate(atom_data):
            x, y, z = map(float, line.split()[1:4])
            atom_type = 1 if i < num_atoms / 2 else 2  # Assigning types for example
            outfile.write(f"{i + 1} {atom_type} {x} {y} {z}\n")

    print(f"LAMMPS data file saved as {output_data_file}")

# Example usage:
xyz_to_lammps_data("combined_surface_water.xyz", "combined_1.data")
