void ft_putstr(char *s);

int main(int ac, char **av) {
	int i = 1;
	while (i < ac)
	{
		ft_putstr(av[i++]);
		ft_putstr("\n");
	}
	return (0);
}