void    handle_sigint(int sig)
{
    printf("\nsignal ctrl c recu");
}

void    handle_sigquit(int sig)
{
    printf("\n signal ctrl \\ recu");
}

void    handle_sigterm(int sig)
{
    printf("\n signal ctrl d recu");
}

void setup_signals()
{
    struct sigaction sa_int;
    struct sigaction sa_quit;
    struct sigaction sa_term;

    sa_int.sa_handler = handle_sigint;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);

    sa_quit.sa_handler = handle_sigquit;
    sigemptyset(&sa_int.sa_mask);
    sa_quit.sa_flags = 0;
    sigaction(SIGINT, &sa_quit, NULL);

    sa_term.sa_handler = handle_sigterm;
    sigemptyset(&sa_int.sa_mask);
    sa_term.sa_flags = 0;
    sigaction(SIGINT, &sa_term, NULL);
}