for  dir in `find . -type f -name "get.sh" -print |  cut -d '/' -f2`  ; do
  cd $dir
  ./get.sh
  cd ..
done

