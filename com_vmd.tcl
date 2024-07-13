# Load the LAMMPS trajectory file
mol new your_structure_file.pdb type pdb  # Load your structure file (if available)
mol addfile v_0.005_eps_0.02_all.lammpstrj type lammpstrj  # Load the LAMMPS trajectory file

# Procedure to calculate center of mass for a given selection
proc calc_center_of_mass {sel} {
    set num_atoms [$sel num]
    set total_mass 0.0
    set com {0.0 0.0 0.0}
    
    for {set i 0} {$i < $num_atoms} {incr i} {
        set mass [lindex [$sel get mass] $i]
        set coords [lindex [$sel get {x y z}] $i]
        
        set total_mass [expr {$total_mass + $mass}]
        set com_x [lindex $com 0]
        set com_y [lindex $com 1]
        set com_z [lindex $com 2]
        
        set com_x [expr {$com_x + [lindex $coords 0] * $mass}]
        set com_y [expr {$com_y + [lindex $coords 1] * $mass}]
        set com_z [expr {$com_z + [lindex $coords 2] * $mass}]
        
        set com [list $com_x $com_y $com_z]
    }
    
    set com_x [expr {[lindex $com 0] / $total_mass}]
    set com_y [expr {[lindex $com 1] / $total_mass}]
    set com_z [expr {[lindex $com 2] / $total_mass}]
    
    return [list $com_x $com_y $com_z]
}

# Loop over all frames and calculate the COM
set num_frames [molinfo top get numframes]
for {set frame 0} {$frame < $num_frames} {incr frame} {
    molinfo top set frame $frame
    set sel [atomselect top all]
    set com [calc_center_of_mass $sel]
    puts "Frame $frame: Center of mass = $com"
    $sel delete
}
