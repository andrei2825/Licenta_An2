package fourth;

public class BadAlbum extends Album{

    public BadAlbum(){}
    public void addSong(Song song) {
        String name = song.getName();
        int id = song.getId();
        int reverse = 0;
        while (id != 0) {
            reverse = reverse * 10 + id % 10;
            id /= 10;
        }
        if (reverse == song.getId() && name.length() == 3) {
            songs.add(song);
        }
    }
}
