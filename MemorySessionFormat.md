# CSE-16 Memory Session Format

## Header
| Size      | Value          | Description        |
|-----------|----------------|--------------------|
| 12 bytes  | "sessionstart" | Magic header       |
| 4 bytes   | "1.1\0"        | Version string     |
| 65536 bytes | raw bytes    | Initial memory snapshot |

## Steps (repeated until "sessionend")
| Size     | Value       | Description   |
|----------|-------------|---------------|
| 4 bytes  | "STEP"      | Step marker   |
| 4 bytes  | int         | Step index    |

### Deltas (repeated until "REG")
| Size    | Value  | Description          |
|---------|--------|----------------------|
| 4 bytes | int    | Address that changed |
| 1 byte  | uint8_t | New value           |

### CPU State
| Size    | Value    | Description     |
|---------|----------|-----------------|
| 3 bytes | "REG"    | Marker          |
| 2 bytes | uint16_t | Register A      |
| 3 bytes | "REG"    | Marker          |
| 2 bytes | uint16_t | Register B      |
| 3 bytes | "REG"    | Marker          |
| 2 bytes | uint16_t | Register C      |
| 3 bytes | "REG"    | Marker          |
| 2 bytes | uint16_t | Register D      |
| 2 bytes | "ST"     | Marker          |
| 2 bytes | uint16_t | Stack pointer   |
| 2 bytes | "PC"     | Marker          |
| 2 bytes | uint16_t | Program counter |

## Footer
| Size     | Value        | Description |
|----------|--------------|-------------|
| 10 bytes | "sessionend" | End marker  |