function! InsertText()
	let cs = 'Computer[ \n]Science'
	call cursor('1', '1')
   while search(cs, 'W') > 0
		exe 'normal! iLongwood University '
		exe 'normal! w'
	endwhile
endfunction

nmap <F2> :call InsertText()<CR>
