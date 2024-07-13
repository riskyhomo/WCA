mol new surface.xyz type xyz 
mol addfile water_box_1.pdb type pdb

animate dup frame 0 0 

set all [atomselect top all]
$all writepdb water_surface.pdb