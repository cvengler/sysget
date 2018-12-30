_sysget()
{
	local cur prev opts
	COMPREPLY=()
	cur="${COMP_WORDS[COMP_CWORD]}"
	prev="${COMP_WORDS[COMP_CWORD-1]}"
	opts="search install remove update upgrade autoremove clean set help about"

	COMPREPLY=( $(compgen -W "${opts}" ${cur}) )
}
complete -F _sysget sysget
