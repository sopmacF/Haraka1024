# Haraka1024

Expand Haraka https://github.com/kste/haraka by adding a Haraka-1024 function, which maps 1024 to 256 bits. The sponge version of Haraka (Haraka_S) is based on the implementation from SPHINCS+ (available here https://sphincs.org/software.html).

# Results

Haraka-512/AES_NI              65.378000 cycles 
Haraka-1024/AES_NI            208.441000 cycles (our implementation)
Haraka-1024/AES_NI (3x 512)   230.070000 cycles 
Haraka-1024 sponge/AES_NI     493.704000 cycles 
Haraka-1024 sponge          18361.418000 cycles (without AES-NI support)
