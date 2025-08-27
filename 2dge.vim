let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/code/2dge/2DGameEngine
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +0 src/main.c
badd +1 include.world.h
badd +91 include/world.h
badd +91 src/world.c
badd +67 include/vector.h
badd +1 include/game_object.h
badd +63 include/world_config.h
badd +1 source/world_config.c
badd +22 src/world_config.c
badd +1 src/engine.c
badd +1 src/windows_renderer.c
badd +1 include/windows_renderer.h
badd +1 include/render.h
badd +1 term://~/code/2dge/2DGameEngine//8397:/bin/bash
badd +12 src/pose.c
badd +177 src/shape.c
badd +1 include/platform.h
badd +1 src/platform.c
badd +1 MakeFile
argglobal
%argdel
$argadd src/main.c
set stal=2
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabrewind
edit src/main.c
argglobal
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 1 - ((0 * winheight(0) + 33) / 67)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1
normal! 0
tabnext
edit src/engine.c
argglobal
balt src/main.c
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 36 - ((17 * winheight(0) + 33) / 67)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 36
normal! 029|
tabnext
edit src/windows_renderer.c
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
wincmd _ | wincmd |
split
1wincmd k
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 120 + 121) / 242)
exe '2resize ' . ((&lines * 33 + 35) / 70)
exe 'vert 2resize ' . ((&columns * 121 + 121) / 242)
exe '3resize ' . ((&lines * 33 + 35) / 70)
exe 'vert 3resize ' . ((&columns * 121 + 121) / 242)
argglobal
balt include/windows_renderer.h
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 66 - ((44 * winheight(0) + 33) / 67)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 66
normal! 034|
lcd ~/code/2dge/2DGameEngine
wincmd w
argglobal
if bufexists(fnamemodify("~/code/2dge/2DGameEngine/include/windows_renderer.h", ":p")) | buffer ~/code/2dge/2DGameEngine/include/windows_renderer.h | else | edit ~/code/2dge/2DGameEngine/include/windows_renderer.h | endif
if &buftype ==# 'terminal'
  silent file ~/code/2dge/2DGameEngine/include/windows_renderer.h
endif
balt ~/code/2dge/2DGameEngine/include/render.h
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 26 - ((12 * winheight(0) + 16) / 33)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 26
normal! 058|
lcd ~/code/2dge/2DGameEngine
wincmd w
argglobal
if bufexists(fnamemodify("~/code/2dge/2DGameEngine/include/render.h", ":p")) | buffer ~/code/2dge/2DGameEngine/include/render.h | else | edit ~/code/2dge/2DGameEngine/include/render.h | endif
if &buftype ==# 'terminal'
  silent file ~/code/2dge/2DGameEngine/include/render.h
endif
balt ~/code/2dge/2DGameEngine/include/windows_renderer.h
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 17 - ((16 * winheight(0) + 16) / 33)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 17
normal! 052|
lcd ~/code/2dge/2DGameEngine
wincmd w
exe 'vert 1resize ' . ((&columns * 120 + 121) / 242)
exe '2resize ' . ((&lines * 33 + 35) / 70)
exe 'vert 2resize ' . ((&columns * 121 + 121) / 242)
exe '3resize ' . ((&lines * 33 + 35) / 70)
exe 'vert 3resize ' . ((&columns * 121 + 121) / 242)
tabnext
argglobal
if bufexists(fnamemodify("term://~/code/2dge/2DGameEngine//8397:/bin/bash", ":p")) | buffer term://~/code/2dge/2DGameEngine//8397:/bin/bash | else | edit term://~/code/2dge/2DGameEngine//8397:/bin/bash | endif
if &buftype ==# 'terminal'
  silent file term://~/code/2dge/2DGameEngine//8397:/bin/bash
endif
balt ~/code/2dge/2DGameEngine/include/world_config.h
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
let s:l = 504 - ((0 * winheight(0) + 33) / 67)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 504
normal! 037|
tabnext
edit ~/code/2dge/2DGameEngine/src/platform.c
argglobal
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 97 - ((27 * winheight(0) + 33) / 67)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 97
normal! 04|
lcd ~/code/2dge/2DGameEngine
tabnext
edit ~/code/2dge/2DGameEngine/MakeFile
argglobal
balt ~/code/2dge/2DGameEngine/src/platform.c
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 1 - ((0 * winheight(0) + 33) / 67)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1
normal! 0
lcd ~/code/2dge/2DGameEngine
tabnext 4
set stal=1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
nohlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
