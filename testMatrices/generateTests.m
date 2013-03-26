for n=1:32;

  A = 10*rand(n);
  lambda = powermethod(A);

  filename = sprintf('matrix_%d.dat',n);
  file = fopen(filename,'wt');

  for i = 1:n
    for j = 1:n
      fprintf(file,'%f\t',A(i,j));
    end
    fprintf(file,'\n');
  end

  fprintf(file,'\n%f\n',lambda);

  fclose(file);

end
