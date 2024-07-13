def merge_xyz(file1, file2, output_file):
    with open(file1, 'r') as f1, open(file2, 'r') as f2, open(output_file, 'w') as out:
        # Read first file
        lines1 = f1.readlines()
        natoms1 = int(lines1[0].strip())
        
        # Read second file
        lines2 = f2.readlines()
        natoms2 = int(lines2[0].strip())
        
        # Total number of atoms
        total_atoms = natoms1 + natoms2
        
        # Write total number of atoms to the output file
        out.write(f"{total_atoms}\n")
        out.write(f"Combined file from {file1} and {file2}\n")
        
        # Write the contents of the first file (skipping the first two lines)
        for line in lines1[2:]:
            out.write(line)
        
        # Write the contents of the second file (skipping the first two lines)
        for line in lines2[2:]:
            out.write(line)

# Merge the files
merge_xyz('surface.xyz', 'water.xyz', 'merged.xyz')
