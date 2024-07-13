# Load the required packages
package require psfgen
package require namdbin

# Load the coordinate file (e.g., DCD or XTC)
set input_file "work.lammpstrj"
set mol [mol load pdb protein.pdb]
mol addfile $input_file waitfor all

# Open an output file to store the center of mass for each frame
set output_file [open "com.dat" "w"]

# Get the number of frames in the trajectory
set num_frames [mol numframes]

# Loop over each frame
for {set frame 0} {$frame < $num_frames} {incr frame} {
    # Switch to the current frame
    mol rewind $input_file $frame

    # Calculate the center of mass for the current frame
    set com [measure center $mol weight mass]

    # Write the center of mass to the output file
    puts $output_file "$frame $com"
}

# Close the output file
close $output_file

# Clean up
mol delete all