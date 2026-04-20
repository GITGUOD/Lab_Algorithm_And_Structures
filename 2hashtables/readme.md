g++ -std=c++11 -g -o main main.cpp
valgrind --leak-check=full --show-leak-kinds=all ./main < data/sample/1.in
valgrind --leak-check=full --show-leak-kinds=all ./main < data/secret/7hube.in


dmins@admins-VMware-Virtual-Platform:~/Desktop/Algoritm_lab/2hashtables$ valgrind --leak-check=full --show-leak-kinds=all ./main < data/secret/7huge.in
==17801== Memcheck, a memory error detector
==17801== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==17801== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==17801== Command: ./main
==17801== 
pg_ascii_tolower 308
==17801== 
==17801== HEAP SUMMARY:
==17801==     in use at exit: 0 bytes in 0 blocks
==17801==   total heap usage: 4,225,451 allocs, 4,225,451 frees, 128,803,975 bytes allocated
==17801== 
==17801== All heap blocks were freed -- no leaks are possible
==17801== 
==17801== For lists of detected and suppressed errors, rerun with: -s
==17801== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

