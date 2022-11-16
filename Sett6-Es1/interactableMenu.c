#include <stdio.h>
#include <stdlib.h>
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

#define DEFAULT_MENU_CHAR '#'
#define DEFAULT_MENU_OPTION_SPACING 1

#define DEFAULT_MENU_TOP_PADDING 2
#define DEFAULT_MENU_RIGHT_PADDING 2
#define DEFAULT_MENU_BOTTOM_PADDING 2
#define DEFAULT_MENU_LEFT_PADDING 2

#define DEFAULT_MENU_TOP_MARGIN 2
#define DEFAULT_MENU_RIGHT_MARGIN 2
#define DEFAULT_MENU_BOTTOM_MARGIN 2
#define DEFAULT_MENU_LEFT_MARGIN 2

#define MINIMUM_WIDTH 4

struct MenuOption
{
    char *Text;
    void (*Function)();
};

struct Menu
{
    char BorderChar;
    int Width;
    int Height;
    int Margin[4]; // Like in CSS (top, right, bottom, left)
    int Padding[4]; // Same as above
    int OptionSpacing;
    int OptionsNumber;
    struct MenuOption *Options;
};

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

struct Menu NewMenu(int charactersWidth, int optionsNumber, struct MenuOption options[])
{
    struct Menu menu;
    menu.BorderChar = DEFAULT_MENU_CHAR;
    menu.Margin[0] = DEFAULT_MENU_TOP_MARGIN;
    menu.Margin[1] = DEFAULT_MENU_RIGHT_MARGIN;
    menu.Margin[2] = DEFAULT_MENU_BOTTOM_MARGIN;
    menu.Margin[3] = DEFAULT_MENU_LEFT_MARGIN;
    menu.Padding[0] = DEFAULT_MENU_TOP_PADDING;
    menu.Padding[1] = DEFAULT_MENU_RIGHT_PADDING;
    menu.Padding[2] = DEFAULT_MENU_BOTTOM_PADDING;
    menu.Padding[3] = DEFAULT_MENU_LEFT_PADDING;
    menu.OptionSpacing = DEFAULT_MENU_OPTION_SPACING;
    menu.OptionsNumber = optionsNumber;
    menu.Options = options;
    menu.Width = charactersWidth; // Maximum Width is defined by user
    menu.Height = menu.OptionsNumber + menu.Margin[0] + menu.Margin[2] + menu.Padding[0] + menu.Padding[2] + ((menu.OptionsNumber - 1) * menu.OptionSpacing);
    // Height is OptionsNumber plus top and bottom margin, top and bottom padding and the OptionSpacing multiplied by OptionsNumber minus 1
    return menu;
}

struct MenuOption NewMenuOption(char optionText[], void (*optionFunction)())
{
    struct MenuOption option;
    option.Text = optionText;
    option.Function = optionFunction;
    return option;
}

enum MenuComponent IdentifyComponent(const struct Menu *menu, int x, int y)
{
    int width = menu->Width;
    int height = menu->Height;

    if(x >= 0 && x < menu->Margin[1] && y >= 0 && y < menu->Margin[0])
        return TopLeftMargin;
    else if(x >= width - menu->Margin[3] && x < width && y >= 0 && y < menu->Margin[0])
        return TopRightMargin;
    else if(x >= width - menu->Margin[3] && x < width && y >= height - menu->Margin[2] && y < height)
        return BottomRightMargin;
    else if(x >= 0 && x < menu->Margin[1] && y >= height - menu->Margin[2] && y < height)
        return BottomLeftMargin;
    else if(y >= 0 && y < menu->Margin[0])
        return TopMargin;
    else if(x >= width - menu->Margin[3] && x < width)
        return RightMargin;
    else if(y >= height - menu->Margin[2] && y < height)
        return BottomMargin;
    else if(x >= 0 && x < menu->Margin[1])
        return LeftMargin;
    else if(x == menu->Margin[1] && y == menu->Margin[0])
        return TopLeftBorder;
    else if(x == width - menu->Margin[3] - 1 && y == menu->Margin[0])
        return TopRightBorder;
    else if(x == width - menu->Margin[3] - 1 && y == height - menu->Margin[2] - 1)
        return BottomRightBorder;
    else if(x == menu->Margin[1] && y == height - menu->Margin[2] - 1)
        return BottomLeftBorder;
    else if(y == menu->Margin[0])
        return TopBorder;
    else if(x == width - menu->Margin[3] - 1)
        return RightBorder;
    else if(y == height - menu->Margin[2] - 1)
        return BottomBorder;
    else if(x == menu->Margin[1])
        return LeftBorder;
    else if(x > menu->Margin[1] && y > menu->Margin[0] && x <= menu->Margin[1] + menu->Padding[1] && y <= menu->Padding[0] + menu->Padding[0])
        return TopLeftPadding;
    else if(x > width - menu->Margin[1] && y > menu->Margin[3] && x <= menu->Margin[1] + menu->Padding[1] && y <= menu->Padding[3] + menu->Padding[3])
        return TopRightPadding;
    else
        return Unknown;
}

void DrawMenu(const struct Menu *menu)
{
    int realWidth = menu->Width - (2 + menu->Margin[1] + menu->Margin[3] + menu->Padding[1] + menu->Padding[3]);
    // realWidth is Width minus 2 (space occupied by border), the right and left margin and the right and left padding
    // This is the width available to the options labels

    if(realWidth < MINIMUM_WIDTH)
    {
        printf("Not enough width to print menu");
    }
    else
    {
        int i, j;
        for(i = 0; i < menu->Height; i++)
        {
            for(j = 0; j < menu->Width; j++)
            {
                enum MenuComponent component = IdentifyComponent(menu, j, i);
                if(component >= TopMargin && component <= TopLeftMargin)
                    printf(".");
                else if(component >= TopBorder && component <= TopLeftBorder)
                    printf("#");
                else if(component >= TopPadding && component <= TopLeftPadding)
                    printf("-");
                else
                    printf(" ");
                
            }
            printf("\n");
        }
    }
}

void StartMenu(const struct Menu *menu)
{
    gotoxy(0, 0);
    DrawMenu(menu);
    gotoxy(0, 0);
}