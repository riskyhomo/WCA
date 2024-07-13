import sys

def xyz_to_lammps(xyz_file, lammps_file):
    # Read XYZ file
    with open(xyz_file, 'r') as f:
        lines = f.readlines()

    # Extract number of atoms and comment
    num_atoms = int(lines[0].strip())
    comment = lines[1].strip()

    # Extract atom data
    atoms = []
    for line in lines[2:]:
        atom_type, x, y, z = line.split()
        atoms.append((atom_type, float(x), float(y), float(z)))

    # Get unique atom types
    atom_types = sorted(set(atom[0] for atom in atoms))
    type_dict = {atom_type: i+1 for i, atom_type in enumerate(atom_types)}

    # Write LAMMPS data file
    with open(lammps_file, 'w') as f:
        f.write(f"# Converted from XYZ file: {comment}\n\n")
        f.write(f"{num_atoms} atoms\n")
        f.write(f"{len(atom_types)} atom types\n\n")

        # Write box dimensions (assuming cubic box)
        max_coord = max(max(abs(atom[i]) for atom in atoms) for i in range(1, 4))
        box_size = max_coord * 2  # Double the maximum coordinate
        f.write(f"-{box_size} {box_size} xlo xhi\n")
        f.write(f"-{box_size} {box_size} ylo yhi\n")
        f.write(f"-{box_size} {box_size} zlo zhi\n\n")

        f.write("Atoms\n\n")
        for i, (atom_type, x, y, z) in enumerate(atoms, 1):
            f.write(f"{i} {type_dict[atom_type]} {x} {y} {z}\n")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python xyz_to_lammps.py input.xyz output.lammps")
        sys.exit(1)

    xyz_file = sys.argv[1]
    lammps_file = sys.argv[2]
    xyz_to_lammps(xyz_file, lammps_file)
    print(f"Conversion complete. LAMMPS data file saved as {lammps_file}")