int winner_index;

    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            for (int k = 0; k < candidate_count; k++)
            {
                if (locked[j][k] == locked[pairs[i].winner][pairs[i].loser])
                {
                    for (int f = 0; f < candidate_count; f++)
                    {
                        if (locked[pairs[i].loser][f] == true)
                        {
                            continue;
                        }
                        else
                        {
                           winner_index = i;
                        }
                    }
                }
            }
        }
    }
