import numpy as np

def filter_sphere(input_file, output_file, cx, cy, cz, radius):
    with open(input_file, 'r') as f_in:
        with open(output_file, 'w') as f_out:
            for line in f_in:
                if line.startswith("ATOM"):
                    coords = line.split()[5:8]
                    x, y, z = map(float, coords)
                    dist = np.sqrt((x - cx)**2 + (y - cy)**2 + (z - cz)**2)
                    if dist <= radius:
                        f_out.write(line)

input_file = 'water.pdb'  
output_file = 'water_sphere_1.pdb'
cx, cy, cz = 0.0, 0.0, 0.0  
radius = 75.0 

filter_sphere(input_file, output_file, cx, cy, cz, radius)
