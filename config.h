/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int minsz     = 20;       /* Minimal height of a client for smfact */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrains Mono:size=10:antialias=true", "siji:pixelsize=16", "JoyPixels:pixelsize=14:antialias=true:autohint=true" };
static const char dmenufont[]       = "JetBrains Mono:size=10:antialias=true";
static const char col_black[]       = "#1d2021";
static const char col_gray1[]       = "#282828";
static const char col_gray2[]       = "#32302f";
static const char col_gray3[]       = "#928474";
static const char col_gray4[]       = "#a89984";
static const char col_white[]       = "#ebdbb2";
static const char col_red[]         = "#cc241d";
static const char col_green[]       = "#98971a";
static const char col_yellow[]      = "#d79921";
static const char col_blue[]        = "#458588";
static const char col_purple[]      = "#b16286";
static const char col_cyan[]        = "#689d6a";
static const char col_orange[]      = "#d65d0e";

static const char *colors[][3]      = {
	/*                    fg            bg          border*/
	[SchemeNorm]      =   { col_gray3,  col_gray1,  col_gray1 },
	[SchemeSel]       =   { col_white,  col_gray1,  col_gray2 },
	[SchemeTagsNorm]  =   { col_gray3,  col_gray1,  col_gray1 },
	[SchemeTagsSel]   =   { col_blue,   col_gray1,  col_gray1 },
	[SchemeInfoNorm]  =   { col_gray3,  col_gray1,  col_gray1 },
	[SchemeInfoSel]   =   { col_white,  col_gray1,  col_gray1 },
  [SchemeStatus]    =   { col_gray3,  col_gray1,  col_gray1 },
};

/* scratchpads */
typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "80x34", NULL };
const char *spcmd2[] = {"st", "-n", "spncmpcpp", "-g", "80x34", "-e", "ncmpcpp", NULL };
static Sp scratchpads[] = {
	/* name           cmd  */
	{"spterm",        spcmd1},
	{"spncmpcpp",     spcmd2},
};

/* tagging */
static const char *tags[] = { "\ue187", "\ue188", "\ue189", "\ue18a", "\ue18b", "\ue18c", "\ue18d", "\ue18e", "\ue18f" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance     title     tags mask     isfloating    monitor */
	{ NULL,      NULL,        NULL,     0,            0,            -1 },
  { NULL,      "spterm",    NULL,     SPTAG(0),     1,            -1 },
  { NULL,      "spncmpcpp", NULL,     SPTAG(1),     1,            -1 },
};

/* layout(s) */
static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
static const float smfact    = 0.00; /* factor of tiled clients [0.00.0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "\ue002",      tile },    /* first entry is default */
	{ "\ue006",      NULL },    /* no layout function means floating behavior */
	{ "\ue001",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	/*{ MODKEY,                       XK_s,      spawn,          {.v = dmenucmd } },*/
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_a,      togglescratch,  {.ui = 1 } },
	{ MODKEY|ShiftMask,             XK_k,      focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_j,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_l,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_g,      togglescratch,  {.ui = 0 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
  { MODKEY,                       XK_j,      setsmfact,      {.f = -0.05} },
  { MODKEY,                       XK_k,      setsmfact,      {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_y,      togglebar,      {0} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_i,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_p,      setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_p,      togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

