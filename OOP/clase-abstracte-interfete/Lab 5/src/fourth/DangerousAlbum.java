package fourth;

public class DangerousAlbum extends Album{

    public DangerousAlbum(){}
    public void addSong(Song song) {
        int id = song.getId();
        boolean ok = false;
        for (int i = 2; i< id / 2; i++) {
            if(id % i == 0){
                ok = true;
                break;
            }
        }
        if (!ok){
            songs.add(song);
        }
    }

}
