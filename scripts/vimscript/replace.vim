echo "source ~/code/mylib/replace.vim"
source ~/.vimrc

function! MyReplace(start, end, num) range
"	let start = a:firstline
"	let end = a:lastline
	for l:i in range(1, a:num)
		execute ":".a:start.",".a:end."s/^\\(\\t*\\)    /\\1\\t/g"
	endfor
"	echo start.",".end."s/^\\(\\t*\\)    /\\1\\t/g"
endfunction

function! MyDebug(start, end) range
	for l:i in range(a:start, a:end)
		let l:line = getline(i)
		" 行首空格替换成tab
"		let l:match = '^\(\t*\)    '
"		while  match(l:line, l:match) >= 0
"			let l:line = substitute(l:line, l:match, '\1\t', 'g')
"		endwhile
"		" if后加空格
"		let l:match = '\([\t ]\)if('
"		if match(l:line, l:match) >= 0
"			let l:line = substitute(l:line, l:match, '\1if (', 'g')
"		endif
"		" for后加空格
"		let l:match = '\([\t ]\)for('
"		if match(l:line, l:match) >= 0
"			let l:line = substitute(l:line, l:match, '\1for (', 'g')
"		endif
"		" while后加空格
"		let l:match = '\([\t ]\)while('
"		if match(l:line, l:match) >= 0
"			let l:line = substitute(l:line, l:match, '\1while (', 'g')
"		endif

		" 逗号后添加空格
		let l:match = '\,\([^ ]\)'
		if match(l:line, l:match) >= 0
			echo l:line
			let l:line = substitute(l:line, l:match, ', \1', 'g')
		endif

"		" 去除行尾空白
"		let l:match = '\s\+$'
"		if match(l:line, l:match) >= 0
"			let l:line = substitute(l:line, l:match, '', 'g')
"		endif
		" 替换当前行
		"call setline(l:i,  l:line)
	endfor
	echo ', xxx'
endfunction

