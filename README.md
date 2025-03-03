# vgu_ethical_hacking
## Lab repo for lab tasks

### 0. Cowsay:
```
docker pull drmint/host-cowsay:latest
docker run -d -p 1339:1339 --name cow drmint/host-cowsay:latest
```

### 1. Baby Challenge:
```
docker pull drmint/host-baby_overflow:latest
docker run -d -p 1338:1338 --name baby drmint/host-baby_overflow:latest
```

### 2. stack challenge:
```
docker pull drmint/host-stack_ovf:latest
docker run -d -p 1337:1337 --name stackovf drmint/host-stack_ovf:latest
```

### 3. Heap Challenge:
```
docker pull drmint/host-heap_ovf:latest
docker run -d -p 1336:1336 --name heapovf drmint/host-heap_ovf:latest
```

### 4. ret2lib challenge:
```
docker pull drmint/host-ret2lib:latest
docker run -d -p 1335:1335 --name ret2lib drmint/host-ret2lib:latest
```
