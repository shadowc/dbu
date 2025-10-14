#pragma once

namespace Console {
    struct Coords {
        Coords() {
            X = 0;
            Y = 0;
        }

        Coords(int x, int y) {
            X = x;
            Y = y;
        }

        int X;
        int Y;
    };

    struct Size {
        Size() {
            Width = 0;
            Height = 0;
        }

        Size(int w, int h) {
            Width = w;
            Height = h;
        }

        int Width;
        int Height;
    };

    struct Mask {
        Mask() {
            Position = Coords(0, 0);
            Dimentions = Size(0, 0);
        }

        Mask(int x, int y, int w, int h) {
            Position = Coords(x, y);
            Dimentions = Size(w, h);
        }

        Coords Position;
        Size Dimentions;
    };

    struct Paddings {
        Paddings() {
            Left = 0;
            Right = 0;
            Top = 0;
            Bottom = 0;
        }

        Paddings(int pValue) {
            Left = pValue;
            Right = pValue;
            Top = pValue;
            Bottom = pValue;
        }

         Paddings(int vValue, int hValue) {
            Left = hValue;
            Right = hValue;
            Top = vValue;
            Bottom = vValue;
        }

        Paddings(int top, int hValue, int bottom) {
            Left = hValue;
            Right = hValue;
            Top = top;
            Bottom = bottom;
        }

        Paddings(int left, int right, int top, int bottom) {
            Left = left;
            Right = right;
            Top = top;
            Bottom = bottom;
        }

        int Left;
        int Right;
        int Top;
        int Bottom;
    };
}
