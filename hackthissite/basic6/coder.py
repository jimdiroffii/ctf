#!/usr/bin/env python3

import argparse

def encode(s: str) -> str:
    """
    Encode a string by adding its index to each character's ASCII code.
    """
    return ''.join(chr(ord(ch) + i) for i, ch in enumerate(s))

def decode(s: str) -> str:
    """
    Decode a string by subtracting each character's index from its ASCII code.
    """
    return ''.join(chr(ord(ch) - i) for i, ch in enumerate(s))

def main():
    parser = argparse.ArgumentParser(
        description="Encode or decode a string by shifting ASCII codes by character position."
    )
    parser.add_argument(
        'mode',
        choices=['e', 'd'],
        help="'e' to encode, 'd' to decode"
    )
    parser.add_argument(
        'text',
        help="The text to encode or decode (wrap in quotes if it contains spaces)"
    )
    args = parser.parse_args()

    if args.mode == 'e':
        output = encode(args.text)
    else:
        output = decode(args.text)

    print(output)

if __name__ == "__main__":
    main()

