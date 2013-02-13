function! InsertText(string compsci)
   while getline(0, end)
		let cs = "Computer Science"
		exe 'normal /'.cs."\<CR> "
   
   endwhile
endfunction
