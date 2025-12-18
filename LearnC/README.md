# Quest 2

```bash
echo "W O R L D" | ./char_decode 0
# → 57 4F 52 4C 44

echo "WORLD" | ./char_decode 0
# → n/a

echo "48 45 4C 4C 4F" | ./char_decode 1
# → H E L L O

echo "48454C4C4F" | ./char_decode 1
# → n/a
```


# Проверка

```clang-format -n src/sourcefile_name.c``` 


# Quest 4

```
gcc door_function.c -lm -o door
```

```
./door > door_data.txt
```

# Quest 5 Bonu

```
gcc door_function.c -mconsole -lm -o door_print
```
