# optics

Implementation of Ordering points to identify the clustering structure algorithm

Compile : 

sh install.sh DIMENSION

(here DIMENSION is dimensions of data - for example data.tsv contains 5 dimensional data)

Test example :

build/optics input_file_name output_file_name minPts eps

Plotting output:

python plot.py input_file_name

(here input file is output from optics algorithm)
