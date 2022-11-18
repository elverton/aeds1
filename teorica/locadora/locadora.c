Locadora* cria_locadora(int max_filmes, int max_clientes, int max_locacoes){
	Locadora *l = (Locadora*)malloc(sizeof(Locadora));
	l->filmes = (Filmes*)malloc(max_filmes*sizeof(Filmes));
	l->clientes = (Cliente*)malloc(max_filmes*sizeof(Cliente));
	l->locacoes = (Locacao*)malloc(max_filmes*sizeof(Locacao));
	l->num_filmes = 0;
	l->num_clientes = 0;
	l->num_locacoes = 0;
	return l
}
