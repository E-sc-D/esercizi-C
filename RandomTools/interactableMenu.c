#include <stdio.h>
#include <stdlib.h>
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

//     __          __     _____  _   _ _____ _   _  _____ 
//     \ \        / /\   |  __ \| \ | |_   _| \ | |/ ____|
//      \ \  /\  / /  \  | |__) |  \| | | | |  \| | |  __ 
//       \ \/  \/ / /\ \ |  _  /| . ` | | | | . ` | | |_ |
//        \  /\  / ____ \| | \ \| |\  |_| |_| |\  | |__| |
//         \/  \/_/    \_\_|  \_\_| \_|_____|_| \_|\_____|
//
//   This is a work in progress! Please do NOT touch anything!
//                  Made by Tommaso De Tommaso
//

struct MenuSpacing
{
    int Top;
    int Right;
    int Bottom;
    int Left;
};

struct MenuSpacing NewMenuSpacing(int top, int right, int bottom, int left)
{
    struct MenuSpacing menuSpacing = { top, right, bottom, left };
    return menuSpacing;
}

struct MenuOption
{
    char *Text;
    void (*Function)();
};

struct MenuOption NewMenuOption(char optionText[], void (*optionFunction)())
{
    struct MenuOption option = { optionText, optionFunction };
    return option;
}

struct MenuStyle
{
    char BorderChar;
    int Width;
    int Height;
    struct MenuSpacing Margins;
    struct MenuSpacing Paddings;
    int OptionSpacing;
} DefaultMenuStyle = { '#', 20, 12, { 2, 2, 2, 2 }, { 2, 2, 2, 2 }, 1 };

struct MenuStyle NewMenuStyle(char borderChar, int width, int height, struct MenuSpacing margins, struct MenuSpacing paddings, int optionSpacing)
{
    struct MenuStyle menuStyle = { borderChar, width, height, margins, paddings, optionSpacing };
    return menuStyle;
}

struct Menu
{
    int OptionsNumber;
    struct MenuOption* Options;
    struct MenuStyle Style;
};

struct Menu NewMenu(int optionsNumber, struct MenuOption options[optionsNumber], struct MenuStyle style)
{
    struct Menu menu = { optionsNumber, options, style };
    return menu;
}

enum MenuComponent
{
    TopMargin,
    TopRightMargin,
    RightMargin,
    BottomRightMargin,
    BottomMargin,
    BottomLeftMargin,
    LeftMargin,
    TopLeftMargin,
    TopPadding,
    TopRightPadding,
    RightPadding,
    BottomRightPadding,
    BottomPadding,
    BottomLeftPadding,
    LeftPadding,
    TopLeftPadding,
    TopBorder,
    TopRightBorder,
    RightBorder,
    BottomRightBorder,
    BottomBorder,
    BottomLeftBorder,
    LeftBorder,
    TopLeftBorder,
    OptionSpacing,
    OptionText,
    Unknown
};

enum MenuComponent GetMenuComponent(const struct Menu menu, int x, int y)
{
    if(x >= 0 && x < menu.Style.Margins.Left && y >= 0 && y < menu.Style.Margins.Top)
        return TopLeftMargin;
    else if(x >= menu.Style.Width - menu.Style.Margins.Right && x < menu.Style.Width && y >= 0 && y < menu.Style.Margins.Top)
        return TopRightMargin;
    else if(x >= menu.Style.Width - menu.Style.Margins.Right && x < menu.Style.Width && y >= menu.Style.Height - menu.Style.Margins.Bottom && y < menu.Style.Height)
        return BottomRightMargin;
    else if(x >= 0 && x < menu.Style.Margins.Left && y >= menu.Style.Height - menu.Style.Margins.Bottom && y < menu.Style.Height)
        return BottomLeftMargin;
    else if(y >= 0 && y < menu.Style.Margins.Top)
        return TopMargin;
    else if(x >= menu.Style.Width - menu.Style.Margins.Right && x < menu.Style.Width)
        return RightMargin;
    else if(y >= menu.Style.Height - menu.Style.Margins.Bottom && y < menu.Style.Height)
        return BottomMargin;
    else if(x >= 0 && x < menu.Style.Margins.Left)
        return LeftMargin;
    else if(x == menu.Style.Margins.Left && y == menu.Style.Margins.Top)
        return TopLeftBorder;
    else if(x == menu.Style.Width - menu.Style.Margins.Right - 1 && y == menu.Style.Margins.Top)
        return TopRightBorder;
    else if(x == menu.Style.Width - menu.Style.Margins.Right - 1 && y == menu.Style.Height - menu.Style.Margins.Bottom - 1)
        return BottomRightBorder;
    else if(x == menu.Style.Margins.Left && y == menu.Style.Height - menu.Style.Margins.Bottom - 1)
        return BottomLeftBorder;
    else if(y == menu.Style.Margins.Top)
        return TopBorder;
    else if(x == menu.Style.Width - menu.Style.Margins.Right - 1)
        return RightBorder;
    else if(y == menu.Style.Height - menu.Style.Margins.Bottom - 1)
        return BottomBorder;
    else if(x == menu.Style.Margins.Left)
        return LeftBorder;
    else if(x > menu.Style.Margins.Left && x <= menu.Style.Margins.Left + menu.Style.Paddings.Left && y > menu.Style.Margins.Top && y <= menu.Style.Margins.Top + menu.Style.Paddings.Top)
        return TopLeftPadding;
    else if(x >= menu.Style.Width - (1 + menu.Style.Margins.Right + menu.Style.Paddings.Right) && x <= menu.Style.Width - menu.Style.Margins.Right && y > menu.Style.Margins.Top && y <= menu.Style.Margins.Top + menu.Style.Paddings.Top)
        return TopRightPadding;
    else if(x >= menu.Style.Width - (1 + menu.Style.Margins.Right + menu.Style.Paddings.Right) && x <= menu.Style.Width - menu.Style.Margins.Right && y >= menu.Style.Height - (1 + menu.Style.Margins.Bottom + menu.Style.Paddings.Bottom) && y <= menu.Style.Height - menu.Style.Margins.Bottom)
        return BottomRightPadding;
    else if(x > menu.Style.Margins.Left && x <= menu.Style.Margins.Left + menu.Style.Paddings.Left && y >= menu.Style.Height - (1 + menu.Style.Margins.Bottom + menu.Style.Paddings.Bottom) && y <= menu.Style.Height - menu.Style.Margins.Bottom)
        return BottomLeftPadding;
    else if(y > menu.Style.Margins.Top && y <= menu.Style.Margins.Top + menu.Style.Paddings.Top)
        return TopPadding;
    else if(x >= menu.Style.Width - (1 + menu.Style.Margins.Right + menu.Style.Paddings.Right) && x <= menu.Style.Width - menu.Style.Margins.Right)
        return RightPadding;
    else if(y >= menu.Style.Height - (1 + menu.Style.Margins.Bottom + menu.Style.Paddings.Bottom) && y <= menu.Style.Height - menu.Style.Margins.Bottom)
        return BottomPadding;
    else if(x > menu.Style.Margins.Left && x <= menu.Style.Margins.Left + menu.Style.Paddings.Left)
        return LeftPadding;
    else if(x > menu.Style.Margins.Left + menu.Style.Paddings.Left && x < menu.Style.Width - (1 + menu.Style.Margins.Right + menu.Style.Paddings.Right) && (y - (1 + menu.Style.Margins.Top + menu.Style.Paddings.Top)) % 2 == 1)
        return OptionSpacing;
    else if(x > menu.Style.Margins.Left + menu.Style.Paddings.Left && x < menu.Style.Width - (1 + menu.Style.Margins.Right + menu.Style.Paddings.Right) && (y - (1 + menu.Style.Margins.Top + menu.Style.Paddings.Top)) % 2 == 0)
        return OptionText;
    else
        return Unknown;
}

void DrawMenu(const struct Menu menu)
{
    int realWidth = menu.Style.Width - (2 + menu.Style.Margins.Right + menu.Style.Margins.Left + menu.Style.Paddings.Right + menu.Style.Paddings.Left);
    // realWidth is Width minus 2 (space occupied by border), the right and left margin and the right and left padding
    // This is the width available to the options labels
    int realHeight = menu.Style.Height - (2 + menu.Style.Margins.Top + menu.Style.Margins.Bottom + menu.Style.Paddings.Top + menu.Style.Paddings.Bottom);
    // realHeight is top and bottom margin plus top and bottom padding

    int minWidth = 4;
    int minHeight = menu.OptionsNumber + (menu.Style.OptionSpacing * (menu.OptionsNumber - 1));

    if(realWidth < minWidth || realHeight < minHeight)
    {
        printf("Not enough space to print menu");
    }
    else
    {   
        int optionIndex = 0, charIndex = 0, i, j;
        for(i = 0; i < menu.Style.Height; i++)
        {
            for(j = 0; j < menu.Style.Width; j++)
            {
                enum MenuComponent component = GetMenuComponent(menu, j, i);
                enum MenuComponent nextComponent = j + 1 < menu.Style.Width ? GetMenuComponent(menu, j + 1, i) : GetMenuComponent(menu, 0, i + 1);

                if(component >= TopMargin && component <= TopLeftPadding || component == OptionSpacing)
                {
                    printf("%c", ' ');
                }
                else if(component >= TopBorder && component <= TopLeftBorder)
                {
                    printf("%c", menu.Style.BorderChar);
                }
                else if(component == OptionText && nextComponent == OptionText && menu.Options[optionIndex].Text[charIndex] != '\0')
                {
                    printf("%c", menu.Options[optionIndex].Text[charIndex]);
                    charIndex++;
                }
                else
                {
                    printf("%c", '.');
                }
            }
            printf("\n");
        }
    }
}

void StartMenu(const struct Menu menu)
{
    gotoxy(0, 0);
    DrawMenu(menu);
    gotoxy(0, 0);
}