#!/bin/bash
echo "Executando L3"
likwid-perfctr -C S0:1 -g L3 -m ./invmat "-r 32 -o saida.txt -i 10" >> ../metricas/v2/L3-32.txt
likwid-perfctr -C S0:1 -g L3 -m ./invmat "-r 33 -o saida.txt -i 10" >> ../metricas/v2/L3-33.txt
likwid-perfctr -C S0:1 -g L3 -m ./invmat "-r 64 -o saida.txt -i 10" >> ../metricas/v2/L3-64.txt
likwid-perfctr -C S0:1 -g L3 -m ./invmat "-r 65 -o saida.txt -i 10" >> ../metricas/v2/L3-65.txt
likwid-perfctr -C S0:1 -g L3 -m ./invmat "-r 128 -o saida.txt -i 10" >> ../metricas/v2/L3-128.txt
likwid-perfctr -C S0:1 -g L3 -m ./invmat "-r 129 -o saida.txt -i 10" >> ../metricas/v2/L3-129.txt
likwid-perfctr -C S0:1 -g L3 -m ./invmat "-r 256 -o saida.txt -i 10" >> ../metricas/v2/L3-256.txt
likwid-perfctr -C S0:1 -g L3 -m ./invmat "-r 257 -o saida.txt -i 10" >> ../metricas/v2/L3-257.txt
likwid-perfctr -C S0:1 -g L3 -m ./invmat "-r 512 -o saida.txt -i 10" >> ../metricas/v2/L3-512.txt
likwid-perfctr -C S0:1 -g L3 -m ./invmat "-r 1000 -o saida.txt -i 10" >> ../metricas/v2/L3-1000.txt
likwid-perfctr -C S0:1 -g L3 -m ./invmat "-r 2000 -o saida.txt -i 10" >> ../metricas/v2/L3-2000.txt

echo "Executando L2CACHE"
likwid-perfctr -C S0:1 -g L2CACHE -m ./invmat "-r 32 -o saida.txt -i 10" >> ../metricas/v2/L2CACHE-32.txt
likwid-perfctr -C S0:1 -g L2CACHE -m ./invmat "-r 33 -o saida.txt -i 10" >> ../metricas/v2/L2CACHE-33.txt
likwid-perfctr -C S0:1 -g L2CACHE -m ./invmat "-r 64 -o saida.txt -i 10" >> ../metricas/v2/L2CACHE-64.txt
likwid-perfctr -C S0:1 -g L2CACHE -m ./invmat "-r 65 -o saida.txt -i 10" >> ../metricas/v2/L2CACHE-65.txt
likwid-perfctr -C S0:1 -g L2CACHE -m ./invmat "-r 128 -o saida.txt -i 10" >> ../metricas/v2/L2CACHE-128.txt
likwid-perfctr -C S0:1 -g L2CACHE -m ./invmat "-r 129 -o saida.txt -i 10" >> ../metricas/v2/L2CACHE-129.txt
likwid-perfctr -C S0:1 -g L2CACHE -m ./invmat "-r 256 -o saida.txt -i 10" >> ../metricas/v2/L2CACHE-256.txt
likwid-perfctr -C S0:1 -g L2CACHE -m ./invmat "-r 257 -o saida.txt -i 10" >> ../metricas/v2/L2CACHE-257.txt
likwid-perfctr -C S0:1 -g L2CACHE -m ./invmat "-r 512 -o saida.txt -i 10" >> ../metricas/v2/L2CACHE-512.txt
likwid-perfctr -C S0:1 -g L2CACHE -m ./invmat "-r 1000 -o saida.txt -i 10" >> ../metricas/v2/L2CACHE-1000.txt
likwid-perfctr -C S0:1 -g L2CACHE -m ./invmat "-r 2000 -o saida.txt -i 10" >> ../metricas/v2/L2CACHE-2000.txt

echo "Executando FLOPS_DP"
likwid-perfctr -C S0:1 -g FLOPS_DP -m ./invmat "-r 32 -o saida.txt -i 10" >> ../metricas/v2/flops-32.txt
likwid-perfctr -C S0:1 -g FLOPS_DP -m ./invmat "-r 33 -o saida.txt -i 10" >> ../metricas/v2/flops-33.txt
likwid-perfctr -C S0:1 -g FLOPS_DP -m ./invmat "-r 64 -o saida.txt -i 10" >> ../metricas/v2/flops-64.txt
likwid-perfctr -C S0:1 -g FLOPS_DP -m ./invmat "-r 65 -o saida.txt -i 10" >> ../metricas/v2/flops-65.txt
likwid-perfctr -C S0:1 -g FLOPS_DP -m ./invmat "-r 128 -o saida.txt -i 10" >> ../metricas/v2/flops-128.txt
likwid-perfctr -C S0:1 -g FLOPS_DP -m ./invmat "-r 129 -o saida.txt -i 10" >> ../metricas/v2/flops-129.txt
likwid-perfctr -C S0:1 -g FLOPS_DP -m ./invmat "-r 256 -o saida.txt -i 10" >> ../metricas/v2/flops-256.txt
likwid-perfctr -C S0:1 -g FLOPS_DP -m ./invmat "-r 257 -o saida.txt -i 10" >> ../metricas/v2/flops-257.txt
likwid-perfctr -C S0:1 -g FLOPS_DP -m ./invmat "-r 512 -o saida.txt -i 10" >> ../metricas/v2/flops-512.txt
likwid-perfctr -C S0:1 -g FLOPS_DP -m ./invmat "-r 1000 -o saida.txt -i 10" >> ../metricas/v2/flops-1000.txt
likwid-perfctr -C S0:1 -g FLOPS_DP -m ./invmat "-r 2000 -o saida.txt -i 10" >> ../metricas/v2/flops-2000.txt
