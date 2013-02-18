function! InsertText()
	let cs = 'Computer[ \n]Science'
	call cursor(1, 1)
   while search(cs, 'W') > 0
		exe 'normal! iLongwood University \<Esc>w'
	endwhile
endfunction

nmap <F2> :source script.vim\<C-W>:call InsertText()\<C-W>
