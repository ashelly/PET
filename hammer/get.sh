mkdir -p source
wget http://www.pst.ifi.lmu.de/~hammer/poker/handeval.tar.gz
gunzip handeval.tar.gz
tar -xvf handeval.tar
mv handeval source
rm  handeval.tar
