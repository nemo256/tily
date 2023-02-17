/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=20" };
static const char dmenufont[]       = "monospace:size=20";
static const char col_black[]       = "#222222";
static const char col_gray1[]       = "#444444";
static const char col_gray2[]       = "#bbbbbb";
static const char col_gray3[]       = "#eeeeee";
static const char col_ruby[]        = "#9b111e";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray2, col_black, col_gray1 },
	[SchemeSel]  = { col_gray3, col_ruby,  col_ruby  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask   isfloating   monitor */
	{ "firefox",  "Navigator",  NULL,  	 	      1,	    	  0,   		 -1 },
	{ "St",  			"st",       	"nmtui",   	    1 << 1,	    0,   		 -1 },
	{ "St",  			"st",       	"htop",   	    1 << 1,	    0,   		 -1 },
	{ "St",  			"st",       	"nvim",   	    1 << 2,	    0,   		 -1 },
	{ "St",  			"st",       	"tty-clock",   	1 << 2,	    0,   		 -1 },
	{ "St",  			"st",       	"newsboat",     1 << 3,	    0,   	 	 -1 },
	{ "St",  			"st",       	"irssi",  	    1 << 3,	    0,   		 -1 },
	{ "St",  			"st",       	"ani-cli",      1 << 3,	    0,   		 -1 },
	{ "St",  			"st",       	"pipe-viewer",  1 << 3,	    0,   		 -1 },
	{ "St",  			"st",       	"tremc",  			1 << 3,	    0,   		 -1 },
	{ "Zathura",  NULL,       	NULL,  					1 << 3,	    0,   		 -1 },
	{ "mpv",  		"gl",       	NULL,  			    1 << 3,	    0,   		 -1 },
};

/* layout(s) */
static const float mfact        = 0.63; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;    /* number of clients in master area */
static const int resizehints    = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre tily-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
// controls
static const char *upbrightness[] = { "brightnessctl", "s", "10%+", NULL };
static const char *downbrightness[] = { "brightnessctl", "s", "10%-", NULL };
static const char *upkbbacklight[] = { "/root/bin/kbbacklight", "UP", NULL };
static const char *downkbbacklight[] = { "/root/bin/kbbacklight", "DOWN", NULL };
static const char *batterylevel[] = { "/root/bin/batterylevel", NULL };
static const char *dunstclose[]   = { "dunstctl", "close", NULL };
static const char *dunstcloseall[]   = { "dunstctl", "close-all", NULL };
static const char *dunsthistory[]   = { "dunstctl", "history-pop", NULL };
static const char *playmusic[]   = { "mpc", "toggle", NULL };
static const char *playnext[]   = { "mpc", "next", NULL };
static const char *playprev[]   = { "mpc", "prev", NULL };
static const char *upvol[]   = { "amixer", "-q", "set", "Master", "5%+", "unmute", NULL };
static const char *downvol[] = { "amixer", "-q", "set", "Master", "5%-", "unmute", NULL };
static const char *mutevol[] = { "amixer", "-q", "set", "Master", "toggle", NULL };
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_black, "-nf", col_gray2, "-sb", col_ruby, "-sf", col_gray3, NULL };

// set st as the default terminal
static const char *termcmd[]  = { "st", NULL };

// terminal commands
static const char *shutdown[] = { "st", "-e", "systemctl", "poweroff",  NULL };
static const char *reboot[] = { "st", "-e", "systemctl", "reboot",  NULL };
static const char *ranger[] = { "st", "-e", "ranger", NULL };
static const char *htop[] = { "st", "-e", "htop", NULL };
static const char *vim[] = { "st", "-e", "nvim", NULL };
static const char *irssi[] = { "st", "-e", "irssi", NULL };
static const char *newsboat[] = { "st", "-e", "newsboat", NULL };
static const char *email[] = { "st", "-e", "neomutt", NULL };
static const char *clock[] = { "st", "-e", "tty-clock", "-scbC", "4", NULL };
static const char *pipeviewer[] = { "st", "-f", "'Fira Code:size=16:style=bold:antialias=true:autohint=true'", "-e", "pipe-viewer", NULL };
static const char *torrent[] = { "st", "-e", "tremc", NULL };
static const char *music[] = { "st", "-e", "ncmpcpp", NULL };
static const char *lynx[] = { "st", "-e", "lynx", NULL };
static const char *anime[] = { "st", "-e", "ani-cli", "--dub", NULL };
static const char *wifi[] = { "st", "-e", "nmtui", NULL };
static const char *watch[] = { "/root/bin/watch", NULL };
static const char *record[] = { "/root/bin/record", NULL };
static const char *vpn[] = { "/root/bin/vpn", NULL };
static const char *background[] = { "/root/bin/background", NULL };
static const char *mykeys[] = { "/root/bin/keys", NULL };
static const char *download[] = { "/root/bin/download", NULL };
static const char *mypointer[] = { "/root/bin/pointer", NULL };
static const char *screenshot[] = { "/root/bin/screenshot", NULL };
static const char *screenshotSelect[] = { "/root/bin/screenshotSelect", NULL };
static const char *photos[] = { "sxiv", "-ftqrb", "/root/Pictures", NULL };
static const char *signal_desktop[] = { "signal-desktop", "--no-sandbox", NULL };
// static const char *tuir[] = { "st", "-e", "tuir", NULL };

// firefox command
static const char *firefox[] = { "firefox", NULL };

// websites
static const char *google[] = { "firefox", "https://www.google.com/", NULL };
static const char *facebook[] = { "firefox", "https://www.facebook.com/", NULL };
static const char *messenger[] = { "firefox", "https://www.messenger.com/", NULL };
static const char *netflix[] = { "firefox", "https://www.netflix.com/", NULL };
static const char *youtube[] = { "firefox", "https://www.youtube.com/", NULL };
static const char *instagram[] = { "firefox", "https://www.instagram.com/", NULL };
static const char *gmail[] = { "firefox", "https://mail.google.com/", NULL };
static const char *aliexpress[] = { "firefox", "https://www.aliexpress.com/", NULL };
static const char *ouedkniss[] = { "firefox", "https://www.ouedkniss.com/", NULL };
static const char *GPhotos[] = { "firefox", "https://photos.google.com/", NULL };
static const char *eccp[] = { "firefox", "https://eccp.poste.dz/", NULL };
static const char *univ[] = { "firefox", "https://fs.univ-boumerdes.dz/", NULL };
static const char *translate[] = { "firefox", "https://translate.google.com/", NULL };
static const char *magnetDL[] = { "firefox", "https://www.magnetdl.com/", NULL };
static const char *contacts[] = { "firefox", "https://contacts.google.com/", NULL };
static const char *github[] = { "firefox", "https://www.github.com/nemo256/", NULL };
static const char *localhost[] = { "firefox", "localhost:3000", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
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
static const Button buttons[] = {
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

