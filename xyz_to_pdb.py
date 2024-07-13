"""USAGE
DIRECT CALL:
python xyz_to_pdb.py 000015.xyz  000015.pdb

## from command line
pdb = convert_xyz('000015.xyz')
pdb = convert_xyz('000015.xyz', export='000015.pdb')
"""

import os
from pdbparser.pdbparser import pdbparser


def convert_xyz(path, export=None):
    assert os.path.isfile(path), "Unable to find given xyz file '%s'"%path
    with open(path, 'r') as fd:
        lines = [l.strip() for l in fd.readlines()]
    #natoms = int(lines[0])
    # skip first 2 lines and build records
    records = []
    for l in lines[2:]:
        el, x, y, z = l.split()
        records.append( { "record_name"       : 'ATOM',
                          "serial_number"     : len(records)+1,
                          "atom_name"         : el,
                          "location_indicator": '',
                          "residue_name"      : 'XYZ',
                          "chain_identifier"  : '',
                          "sequence_number"   : len(records)+1,
                          "code_of_insertion" : '',
                          "coordinates_x"     : float(x),
                          "coordinates_y"     : float(y),
                          "coordinates_z"     : float(z),
                          "occupancy"         : 1.0,
                          "temperature_factor": 0.0,
                          "segment_identifier": '',
                          "element_symbol"    : el,
                          "charge"            : '',
                          } )
    # create and return pdb
    pdb = pdbparser(filePath = None)
    pdb.records = records
    # export
    if export is not None:
        pdb.export_pdb(export)
    # return
    return pdb


if __name__ == '__main__':
    import sys
    assert len(sys.argv)==3, "first argument must be xyz file and second xyz export file"
    path   = sys.argv[1]
    export = sys.argv[2]
    #   convert and export
    convert_xyz(path=path, export=export)
