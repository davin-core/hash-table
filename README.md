# Hash Table (C++)

A small hash table project I built to practice core data structure behavior in modern C++.

It supports:

- insert / update
- search
- delete
- printing table contents
- resizing up and down

Internally it uses:

- `std::unique_ptr` for memory safety
- open addressing with linear probing
- prime-sized table growth/shrink

---

## Why this project exists

I wanted a version of a hash table that’s simple enough to read, but still close to how a real one works (collisions, probing, load factor, resizing).

---

## Project layout

- `src/hash_table.h` — structs + function declarations
- `src/hash_table.cpp` — hash table logic
- `src/prime.h` / `src/prime.cpp` — prime helpers for resize targets
- `src/main.cpp` — console menu to try operations interactively

---

## Build (Windows + CMake)

From the project root:

```powershell
cmake -S . -B build
cmake --build build --config Release
```

Run:

```powershell
.\build\Release\main.exe
```

---

## Console menu

The app currently has options for:

1. Insert/Update key-value  
2. Search key  
3. Delete key  
4. Print table  
5. Resize UP (manual)  
6. Resize DOWN (manual)  
7. Exit  

---

## Notes

- `unique_ptr` handles memory cleanup automatically.
- A delete operation is still needed for hash-table behavior (not memory behavior).
- Search currently returns an empty string when not found, so empty-string values can be ambiguous.

---

## Next improvements (optional)

- Add tombstone handling for delete in linear probing
- Return `bool`/`std::optional<std::string>` from search
- Add unit tests for insert/search/delete/resize
- Add automatic resize thresholds only (remove manual menu options)

---

## License

MIT 