#ifndef AUDIO_SEQPLAYER_H
#define AUDIO_SEQPLAYER_H

#include <PR/ultratypes.h>

#include <!sm64/src/audio/internal.h>
#include <!sm64/src/audio/playback.h>

void seq_channel_layer_disable(struct SequenceChannelLayer *seqPlayer);
void sequence_channel_disable(struct SequenceChannel *seqPlayer);
void sequence_player_disable(struct SequencePlayer *seqPlayer);
void audio_list_push_back(struct AudioListItem *list, struct AudioListItem *item);
void *audio_list_pop_back(struct AudioListItem *list);
void sequence_channel_set_volume(struct SequenceChannel *seqChannel, u8 volume);
void process_sequences(s32 iterationsRemaining);
void init_sequence_player(u32 player);
void init_sequence_players(void);

#endif // AUDIO_SEQPLAYER_H
