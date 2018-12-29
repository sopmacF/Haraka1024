# Haraka1024

Expand Haraka https://github.com/kste/haraka by adding a Haraka-1024 function, which maps 1024 to 256 bits. The sponge version of Haraka (Haraka_S) is based on the implementation from SPHINCS+ (available here https://sphincs.org/software.html).

# Results

Haraka-512/AES_NI&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;65.378000 cycles<br>
Haraka-1024/AES_NI&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;208.441000 cycles (our implementation)<br>
Haraka-1024/AES_NI (3x 512)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;230.070000 cycles<br>
Haraka-1024 sponge/AES_NI&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;493.704000 cycles<br> 
Haraka-1024 sponge&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;18361.418000 cycles (without AES-NI support)<br>
Editing Haraka1024_README.md at master · sopmacF_Haraka1024
