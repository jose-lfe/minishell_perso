#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

void execute_pipeline(char ***commands, int num_cmds) {
    int i;
    int pipe_fd[2];
    int prev_fd = 0; // Fd de lecture du pipe précédent

    for (i = 0; i < num_cmds; i++) {
        // Créer un pipe
        if (i < num_cmds - 1) {
            pipe(pipe_fd);
        }

        pid_t pid = fork();
        if (pid == 0) {
            // Dans le processus enfant
            if (prev_fd != 0) {
                dup2(prev_fd, STDIN_FILENO); // Redirige l'entrée depuis le pipe précédent
                close(prev_fd);
            }
            if (i < num_cmds - 1) {
                dup2(pipe_fd[1], STDOUT_FILENO); // Redirige la sortie vers le pipe actuel
                close(pipe_fd[1]);
            }

            // Exécuter la commande
            execvp(commands[i][0], commands[i]);
            perror("execvp échoué");
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("fork échoué");
            exit(EXIT_FAILURE);
        }

        // Dans le processus parent
        if (prev_fd != 0) {
            close(prev_fd); // Ferme le fd de lecture du pipe précédent
        }
        if (i < num_cmds - 1) {
            close(pipe_fd[1]); // Ferme l'extrémité d'écriture du pipe actuel
        }
        prev_fd = pipe_fd[0]; // Le pipe de lecture actuel devient le précédent
    }

    // Attendre que tous les enfants se terminent et récupérer les valeurs de retour
    int status;
    for (i = 0; i < num_cmds; i++) {
        pid_t wpid = waitpid(-1, &status, 0); // Attendre un enfant

        if (wpid > 0) {
            if (WIFEXITED(status)) { // Vérifie si le processus s'est terminé normalement
                int exit_code = WEXITSTATUS(status); // Récupère le code de sortie
                printf("Le code de sortie de l'enfant %d est %d\n", wpid, exit_code);
            } else {
                printf("L'enfant %d ne s'est pas terminé normalement\n", wpid);
            }
        }
    }
}

int main() {
    // Exemple d'utilisation
    char *commands[][2] = {
        {"ls", NULL},
        {"grep", "txt"},
        {"wc", "-l"}
    };
    execute_pipeline((char ***)commands, 3);
    return 0;
}
