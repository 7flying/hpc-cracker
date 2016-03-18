# hpc-cracker
Parallel cracker

0) Hasher -> sha256
   ./hash "hello"
   fefefefejkgjwhiou95404u1
   
1) Sequential cracker
   ./cracker "feriuopri45i0" -l 3 -h 6 -a "0123456789"
   FOUND! hash(hello) = "ojefioñhqriorqw34353"
   
   ```
   found = false
   while != found
   {
       candidate = nextCandidate(index, 3, 6, "0123456789")
       if (hash(candidate) == "ojefioñhqriorqw34353")
       {
           found = true
       }
           
   }
   if (found)
   {
       printf("FOUND");
   }
   ```
   
2) Cracker OpenMP

3) Cracker MPI
   
