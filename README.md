# Haraka1024

Expand Haraka https://github.com/kste/haraka by adding a Haraka-1024 function, which maps 1024 to 256 bits. The sponge version of Haraka (Haraka_S) is based on the implementation from SPHINCS+ (available here https://sphincs.org/software.html).

# Results

Version                       | clock cycles
------------------------------|---------------------
Haraka-512/NI       64 ->  32 |&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;59.349000 cycles
Haraka-768/NI       96 ->  32 |&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;116.693000 cycles (our implementation)
Haraka-1024/NI     128 ->  32 |&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;143.012000 cycles (our implementation)
                              |
haraka512_perm_NI   64 ->  64 |
haraka1024_perm_NI 128 -> 128 |
                              |
Haraka-512_S/NI    128 ->  32 |&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;470.932000 cycles
Haraka-1024_S/NI   128 ->  32 |&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;415.238000 cycles (our implementation)
Haraka-512_S/NI     96 ->  32 |&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;382.071000 cycles
Haraka-1024_S/NI    96 ->  32 |&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;415.046000 cycles